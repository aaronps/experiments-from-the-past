#include "VideoInput.hpp"

#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>

VideoInput::VideoInput()
 : fd(-1), last_used_buffer(-1), used_bytes(0),
   isCapturing(false), isInitialized(false)
{
    // nothing
}

VideoInput::~VideoInput()
{
    closeDevice();
}

int VideoInput::do_ioctl(int request, void *arg)
{
    int r;

    do
    {
        r = ioctl( fd, request, arg );
    } while (-1 == r && EINTR == errno);

    return r;
}

bool VideoInput::openDevice(const char * device_name)
{
    dev_name = device_name;
    struct stat st;

    if ( stat(device_name, &st) == -1 )
    {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n",
                device_name, errno, strerror(errno));
        return false;
    }

    if ( ! S_ISCHR(st.st_mode) )
    {
        fprintf(stderr, "%s is no device\n", device_name);
        return false;
    }

    fd = open(device_name, O_RDWR /* required */ | O_NONBLOCK, 0);

    if ( fd == -1 )
    {
        fprintf(stderr, "Cannot open '%s': %d, %s\n",
                device_name, errno, strerror(errno));
                
        return false;
    }
    
    print_capabilities();
    print_formats();
    
    return init_device();
}

void VideoInput::closeDevice()
{
    if ( fd != -1)
    {
        endCapture();
        deinit_device();
        close(fd);
        fd = -1;
    }
}

bool VideoInput::init_device()
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    if ( do_ioctl(VIDIOC_QUERYCAP, &cap) == -1)
    {
        if (EINVAL == errno)
        {
            fprintf(stderr, "%s is no V4L2 device\n", dev_name.c_str());
        }
        else
        {
            fprintf(stderr, "VIDIOC_QUERYCAP");
        }
        
        closeDevice();
        return false;
    }

    if ( ! cap.capabilities & V4L2_CAP_VIDEO_CAPTURE )
    {
        fprintf(stderr, "%s is no video capture device\n", dev_name.c_str());
        closeDevice();
        return false;
    }

    if ( ! cap.capabilities & V4L2_CAP_STREAMING )
    {
        fprintf(stderr, "%s does not support streaming i/o (required)\n", dev_name.c_str());
        closeDevice();
        return false;
    }

    /* Select video input, video standard and tune here. */

    memset( &cropcap, 0, sizeof(cropcap) );
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ( do_ioctl(VIDIOC_CROPCAP, &cropcap) == 0 )
    {
        printf("Def rect is: %d,%d size: %d,%d",
               cropcap.defrect.left,
               cropcap.defrect.top,
               cropcap.defrect.width,
               cropcap.defrect.height );
               
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        do_ioctl(VIDIOC_S_CROP, &crop); // EINVAL = crop not support
    }

    memset(&fmt, 0, sizeof(fmt));

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
//        if (force_format) {
    fmt.fmt.pix.width       = VIDEOW;
    fmt.fmt.pix.height      = VIDEOH;
//    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    if ( do_ioctl(VIDIOC_S_FMT, &fmt) == -1)
    {
        fprintf(stderr, "Couldn't set format\n");
        closeDevice();
        return false;
    }

    /* Note VIDIOC_S_FMT may change width and height. */
//        } else {
//                /* Preserve original settings as set by v4l2-ctl for example */
//                if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
//                        errno_exit("VIDIOC_G_FMT");
//        }

    /* Buggy driver paranoia. */
//        min = fmt.fmt.pix.width * 2;
//        if (fmt.fmt.pix.bytesperline < min) fmt.fmt.pix.bytesperline = min;
//        min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
//        if (fmt.fmt.pix.sizeimage < min) fmt.fmt.pix.sizeimage = min;

    return init_mmap();
}

bool VideoInput::init_mmap()
{
    struct v4l2_requestbuffers req;

    memset(&req, 0, sizeof(req));

    req.count = 4; // num buffers wanted
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if ( do_ioctl(VIDIOC_REQBUFS, &req) == -1 )
    {
        if (EINVAL == errno)
        {
            fprintf(stderr, "%s does not support memory mapping\n", dev_name.c_str());
        }
        else
        {
            fprintf(stderr, "VIDIOC_REQBUFS");
        }
        closeDevice();
        return false;
    }

    if (req.count < 2)
    {
        fprintf(stderr, "Insufficient buffer memory on %s\n", dev_name.c_str());
        closeDevice();
        return false;
    }

    printf("Allocating %d buffers\n", req.count);

//    buffers = (buffer*)calloc(req.count, sizeof(*buffers));
//
//    if ( !buffers )
//    {
//        fprintf(stderr, "Out of memory\n");
//        closeDevice();
//        return false;
//    }

    for ( unsigned n = 0; n < req.count; ++n )
    {
        struct v4l2_buffer buf = {0};

        buf.type    = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory  = V4L2_MEMORY_MMAP;
        buf.index   = n;

        if ( do_ioctl(VIDIOC_QUERYBUF, &buf) == -1 )
        {
            fprintf(stderr, "Error querying buffer %d", n);
            closeDevice();
            return false;
        }
        
        void * ptr = mmap(  NULL /* start anywhere */,
                            buf.length,
                            PROT_READ | PROT_WRITE /* required */,
                            MAP_SHARED /* recommended */,
                            fd,
                            buf.m.offset);
                            
        if ( ptr == MAP_FAILED )
        {
            fprintf(stderr, "Error mapping buffer %d", n);
            closeDevice();
            return false;
        }
        
        buffers.push_back(ptr);
        buffers_sizes.push_back(buf.length);
    }
    
    return true;
}

void VideoInput::deinit_mmap()
{
    for ( unsigned i = 0; i < buffers.size(); ++i )
    {
        munmap(buffers[i], buffers_sizes[i]);
        // do something if error?
    }
    
    buffers.clear();
    buffers_sizes.clear();
}

void VideoInput::deinit_device()
{
    deinit_mmap();
}

bool VideoInput::beginCapture()
{

    // begins in one so when we capture the first frame
    // we push the first buffer there.
    for ( unsigned i = 1; i < buffers.size() ; ++i)
    {
        struct v4l2_buffer buf = {0};

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if ( do_ioctl(VIDIOC_QBUF, &buf) == -1 )
        {
            fprintf(stderr, "VIDIOC_QBUF at %d\n", i);
            return false;
        }
    }
    
    last_used_buffer = -1;
        
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if ( do_ioctl(VIDIOC_STREAMON, &type) == -1 )
    {
        fprintf(stderr, "Error activating stream\n");
        return false;
    }
    return true;
}

void VideoInput::endCapture()
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    do_ioctl(VIDIOC_STREAMOFF, &type);
}

bool VideoInput::captureFrame()
{
    struct v4l2_buffer buf = {0};

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    
    if ( last_used_buffer >= 0 )
    {
        buf.index = last_used_buffer;
        last_used_buffer = -1; // XXX risk
        if ( do_ioctl(VIDIOC_QBUF, &buf) == -1 )
        {
            fprintf(stderr, "VIDIOC_QBUF at %d\n", buf.index);
            return false;
        }
    }
    
    while ( 1 )
    {
        fd_set fds;
        struct timeval tv;
        int r;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select(fd + 1, &fds, NULL, NULL, &tv);

        if (-1 == r)
        {
            if (EINTR == errno) continue;
            fprintf(stderr, "Error in select\n");
            return false;
        }

        if (0 == r)
        {
            fprintf(stderr, "Nothing to capture\n");
            return false;
        }

        if ( do_ioctl(VIDIOC_DQBUF, &buf) == -1)
        {
            switch (errno)
            {
                case EAGAIN:
                    return false;

                case EIO:
                    /* Could ignore EIO, see spec. */
                    /* fall through */

                default:
                    fprintf(stderr, "Error dequeing buffer\n");
            }
        }
        
        last_used_buffer = buf.index;
        used_bytes = buf.bytesused;
        break;
    }
    return true;
}

bool VideoInput::frameYToBuffer8(void * dest)
{
    uint8_t * dptr = static_cast<uint8_t*>(dest);
    uint8_t * sptr = static_cast<uint8_t*>(buffers[last_used_buffer]);

    sptr++;
    for ( int y = 0; y < VIDEOH; ++y )
    {
        for ( int x = 0; x < VIDEOW; x++ )
        {
            *dptr = *sptr;
            
            sptr += 2;
            ++dptr;
        }
    }
    
    return true;
}

bool VideoInput::frameUToBuffer8(void * dest)
{
    uint8_t * dptr = static_cast<uint8_t*>(dest);
    uint8_t * sptr = static_cast<uint8_t*>(buffers[last_used_buffer]);
    sptr++;

    for ( int y = 0; y < VIDEOH; ++y )
    {
        for ( int x = 0; x < VIDEOW; x+=2 )
        {
            *dptr++ = *sptr;
            *dptr++ = *sptr;
            sptr += 4;
        }
    }
    
    return true;
}

bool VideoInput::frameVToBuffer8(void * dest)
{
    uint8_t * dptr = static_cast<uint8_t*>(dest);
    uint8_t * sptr = static_cast<uint8_t*>(buffers[last_used_buffer]);
    sptr++;

    for ( int y = 0; y < VIDEOH; ++y )
    {
        for ( int x = 0; x < VIDEOW; x+=2 )
        {
            *dptr++ = *sptr;
            *dptr++ = *sptr;
            sptr += 4;
        }
    }
    
    return true;
}

void VideoInput::print_capabilities()
{
    v4l2_capability caps = {0};

    if ( ! do_ioctl(VIDIOC_QUERYCAP, &caps) )
    {
        printf("driver '%s'\n", caps.driver);
        printf("card '%s'\n",   caps.card);
        printf("bus '%s'\n",    caps.bus_info);
        printf("version: %u.%u.%u\n",
                                (caps.version >> 16)& 0xff,
                                (caps.version >> 8) & 0xff,
                                (caps.version)      & 0xff);

#define CAPCHECK(c) if ( caps.capabilities & c ) printf( #c "\n" )

 CAPCHECK(V4L2_CAP_VIDEO_CAPTURE);
 CAPCHECK(V4L2_CAP_VIDEO_OUTPUT);
 CAPCHECK(V4L2_CAP_VIDEO_OVERLAY);
 CAPCHECK(V4L2_CAP_VBI_CAPTURE);
 CAPCHECK(V4L2_CAP_VBI_OUTPUT);
 CAPCHECK(V4L2_CAP_SLICED_VBI_CAPTURE);
 CAPCHECK(V4L2_CAP_SLICED_VBI_OUTPUT);
 CAPCHECK(V4L2_CAP_RDS_CAPTURE);
 CAPCHECK(V4L2_CAP_VIDEO_OUTPUT_OVERLAY);
 CAPCHECK(V4L2_CAP_HW_FREQ_SEEK);
 CAPCHECK(V4L2_CAP_RDS_OUTPUT);

 CAPCHECK(V4L2_CAP_TUNER);
 CAPCHECK(V4L2_CAP_AUDIO);
 CAPCHECK(V4L2_CAP_RADIO);
 CAPCHECK(V4L2_CAP_MODULATOR);

 CAPCHECK(V4L2_CAP_READWRITE);
 CAPCHECK(V4L2_CAP_ASYNCIO);
 CAPCHECK(V4L2_CAP_STREAMING);

#undef CAPCHECK
    }
}

void VideoInput::print_formats()
{
    v4l2_fmtdesc fmt = {0};
    int fmt_index = 0;

    fmt.index = fmt_index;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    while ( ! do_ioctl(VIDIOC_ENUM_FMT, &fmt) )
    {
        printf("#%02d %-31s %c%c%c%c %s %s\n",
               fmt_index,
               fmt.description,
               (fmt.pixelformat      ) & 0xff,
               (fmt.pixelformat >>  8) & 0xff,
               (fmt.pixelformat >> 16) & 0xff,
               (fmt.pixelformat >> 24) & 0xff,
               fmt.flags & V4L2_FMT_FLAG_COMPRESSED ? "compressed":"normal",
               fmt.flags & V4L2_FMT_FLAG_EMULATED ? "emulated":"real"
               );

        fmt_index++;
        fmt.index = fmt_index;
    }
}

#if 0
void yuv2rgb(int y, int u, int v, unsigned char *p)
{
   int r1, g1, b1;
   int c = y-16, d = u - 128, e = v - 128;

   r1 = (298 * c           + 409 * e + 128) >> 8;
   g1 = (298 * c - 100 * d - 208 * e + 128) >> 8;
   b1 = (298 * c + 516 * d           + 128) >> 8;

   // Even with proper conversion, some values still need clipping.

   if (r1 > 255) r1 = 255;
   if (g1 > 255) g1 = 255;
   if (b1 > 255) b1 = 255;
   if (r1 < 0) r1 = 0;
   if (g1 < 0) g1 = 0;
   if (b1 < 0) b1 = 0;

   *p++ = r1 ;
//   *p++ = r1 ;
//   *p++ = 0 ;
   *p++ = g1 ;
//   *p++ = 0 ;
   *p++ = b1 ;
//   *p++ = 255;
}

 unsigned char * line = (unsigned char *) gsurface->pixels;
            unsigned char * ptrxx = line;

            Uint8 * pixel_16 = (Uint8 *)buffers[buf.index].start;

            for ( int y = 0; y < 480; y++)
            {
                for ( int x=0; x<640; x+=2)
                {
                    int y, u, v, y2;
//                    char r, g, b;

                    //pixel_24 = pBuffer;   // + bih.biWidth*bih.biHeight * 3

//                    v  = ((*pixel_16 & 0x000000ff));
//                    y  = ((*pixel_16 & 0x0000ff00)>>8);
//                    u  = ((*pixel_16 & 0x00ff0000)>>16);
//                    y2 = ((*pixel_16 & 0xff000000)>>24);

                    Uint8 y0 = *pixel_16++;
                    Uint8 v0 = *pixel_16++;
                    Uint8 y1 = *pixel_16++;
                    Uint8 u0 = *pixel_16++;

//                    yuv2rgb(y, u, v, ptrxx);            // 1st pixel
//                    yuv2rgb(y0, u0, v0, ptrxx);            // 1st pixel
//                    ptrxx += 3;

//                    yuv2rgb(y2, u, v, ptrxx);            // 2nd pixel
//                    yuv2rgb(y1, u0, v0, ptrxx);            // 2nd pixel
//                    ptrxx += 3;

                    *ptrxx++ = y0;
//                    *ptrxx++ = y0;
//                    *ptrxx++ = y0;
//                    *ptrxx++ = 255;

                    *ptrxx++ = y1;
//                    *ptrxx++ = y1;
//                    *ptrxx++ = y1;
//                    *ptrxx++ = 255;

//                    int z = y0 + 1.140f * v0;
//                    *ptrxx++ = std::max(0, std::min((int)(y0 + 1.140f * v0), 255));
//                    *ptrxx++ = std::max(0, std::min((int )(y0 - 0.395f * u0 - 0.581f * v0), 255));
//                    *ptrxx++ = std::max(0, std::min((int )(y0 + 2.032f * u0), 255));
//                    *ptrxx++ = 0;

//                    z = y2 + 1.140f * v0;
//                    *ptrxx++ = std::max(0, std::min((int )(y1 + 1.140f * v0), 255));
//                    *ptrxx++ = std::max(0, std::min((int )(y1 - 0.395f * u0 - 0.581f * v0), 255));
//                    *ptrxx++ = std::max(0, std::min((int )(y1 + 2.032f * u0), 255));
//                    *ptrxx++ = 0;

                }

                line += gsurface->pitch;
                ptrxx = line;
            }

//            memcpy(s->pixels, buffers[buf.index].start, buf.bytesused);
//            process_image(buffers[buf.index].start, buf.bytesused);

//            if (-1 == xioctl(cam, VIDIOC_QBUF, &buf))
//                    errno_exit("VIDIOC_QBUF");
#endif
