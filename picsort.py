import os
import time
import shutil
import piexif

def get_datetime(filename):
    """Returns the date and time of a picture checking exif fields, if date is not there use the last modified time of the picture"""
    #print("Doing ", filename)
    tags = piexif.load(filename)
    if "0th" in tags and piexif.ImageIFD.DateTime in tags["0th"]:
        return sanitize_time(tags["0th"][piexif.ImageIFD.DateTime].decode())

    if "Image" in tags and piexif.ImageIFD.DateTime in tags["Image"]:
        return sanitize_time(tags["Image"][piexif.ImageIFD.DateTime].decode())

    if "Exif" in tags:
        if piexif.ExifIFD.DateTimeOriginal in tags["Exif"]:
            dt = tags["Exif"][piexif.ExifIFD.DateTimeOriginal]
            if len(dt) > 0:
                return sanitize_time(dt.decode())

        if piexif.ExifIFD.DateTimeDigitized in tags["Exif"]:
            dt = tags["Exif"][piexif.ExifIFD.DateTimeDigitized]
            if len(dt) > 0:
                return sanitize_time(dt.decode())
    
    return time.strftime("%Y-%m-%d %H%M%S", time.gmtime(os.path.getmtime(filename)))
    
def sanitize_time(strtime):
    """Returns the sanitized time "yyyy-mm-dd hhMMss" from the format "yyyy:mm:dd hh:MM:ss" """
    parts = strtime.split()
    return "%s %s" % (parts[0].replace(":","-"), parts[1].replace(":",""))

def make_copy_list(dir_base):
    """Scans the directory for pictures (jpg) and returns a dictionary with the files and their new names"""

    destlist = {}

    for base, dirs, files in os.walk(dir_base):
        #print("Base is '%s'" % base)
        for file in files:
            if file.lower().endswith(".jpg"):
                fullpath = os.path.join(base, file)
                dt = get_datetime(fullpath)
            
                final_name = "%s %s" % (dt, file.lower())
                if final_name in destlist:
                    print("duplicated name: %s" % final_name)
                else:
                    destlist[final_name] = fullpath

    return destlist

def write_copylist(filename, list):
    """Writes the list to a text file for review"""

    ofile = open(filename,"w")

    for k in sorted(list.keys()):
        print("%s -> %s" % (k,list[k]), file=ofile)

    ofile.close();

def copy_files(list, dest, delete=False):
    for k in sorted(list.keys()):
        dst = os.path.join(dest,k)
        if delete:
            shutil.move(list[k], dst)
        else:
            shutil.copy2(list[k], dst)

        #if delete:
        #    os.remove(list[k])



BASEDIR = "d:\\Photos\\huiphone"
DESTDIR = "d:\\Photos2\\huiphone1"
DODELETE = True

print("Creating '%s' directory" % DESTDIR)

os.makedirs(DESTDIR)

print("Scanning '%s'" % BASEDIR)

destlist = make_copy_list(BASEDIR)

print("Saving result to text file")

write_copylist("move_list.txt", destlist)

print("Doing operation")
            
copy_files(destlist, DESTDIR, delete=DODELETE)



