#ifndef VIDEOINPUT_HPP
#define VIDEOINPUT_HPP

#include <string>
#include <vector>

#define VIDEOW (352)
#define VIDEOH (288)
/*
class PixelFormatConverter
{
public:
    PixelFormatConverter();
    virtual ~PixelFormatConverter();
};
*/
/*

class DataBuffer
{
private:
    DataBuffer(const DataBuffer& other); // no copy con
    DataBuffer& operator=(const DataBuffer& other); // no eq

    void * data;
    int size;
    bool managed;
public:
    DataBuffer() : data(0), size(0), managed(true) {}
    
    DataBuffer(int size)
    {
        data = uint8_t[size];
        if ( data )
        {
            managed = true;
            this->size = size;
        }
    }
    
    DataBuffer(void * data, int size)
    {
        this->data = data;
        this->size = size;
        this->managed = false;
    }
    
    ~DataBuffer()
    {
        if ( data && managed )
        {
            delete[] data;
            size = 0;
            data = 0;
        }
    }
    
};

class Image
{
public:
    Image()
      : width(0), height(0), bytesperline(0), bitsperpixel(0),
        data(0), datalen(0)
    {
        // nothing
    }
    
    Image(int width, int height, int bitsperpixel, void * data = 0, int datalen = 0)
    {
        this->width = width;
        this->height = height;
        
    }
    ~Image();

private:
    int width;
    int height;
    int bytesperline;
    int bitsperpixel;
    void * data;
    int datalen;
};

*/

class VideoInput
{
public:
    VideoInput();
    ~VideoInput();
    
    bool openDevice(const char * device_name);
    void closeDevice();
    
    bool beginCapture();
    bool captureFrame();
    bool frameYToBuffer8(void * dest);
    bool frameUToBuffer8(void * dest);
    bool frameVToBuffer8(void * dest);
    void endCapture();

private:
    int                 fd;
    std::vector<void *> buffers;
    std::vector<unsigned> buffers_sizes;
    int                 last_used_buffer;
    int                 used_bytes;
    std::string         dev_name;
    bool                isCapturing;
    bool                isInitialized;
    
    int do_ioctl(int request, void *arg);

    bool init_device();
    bool init_mmap();
    void deinit_mmap();
    void deinit_device();
    
    
    void print_formats();
    void print_capabilities();
};

#endif // VIDEOINPUT_HPP
