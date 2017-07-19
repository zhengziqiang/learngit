import os
import Image
img=Image.open('/home/zzq/learngit/latex/poster/a0_portrait/figures/logo.jpg')
# print img.shape
def ResizeImage(filein, fileout, width, height, type):
    img = Image.open(filein)
    out = img.resize((width, height),Image.ANTIALIAS) #resize image with high-quality
    out.save(fileout, type)
out=img.resize((200,200),Image.ANTIALIAS)
fileout='/home/zzq/learngit/latex/poster/a0_portrait/figures/logo_resize.jpg'
out.save(fileout)
# if __name__ == "__main__":
#     filein = r'img3.jpg'
#     fileout = r'img.png'
#     width = 363
#     height = 363
#     type = 'png'
#     ResizeImage(filein, fileout, width, height, type)