#-------------------------------------------------
#
# Project created by QtCreator 2018-03-30T10:51:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car_recog_search_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    car_predict.cpp \
    car_search.cpp

HEADERS  += mainwindow.h \
    car_label_predict.h \
    car_predict.h \
    car_search.h

FORMS    += mainwindow.ui \
    car_predict.ui \
    car_search.ui
INCLUDEPATH += /usr/local/include\
               /usr/local/include/opencv\
               /usr/local/include/opencv2
LIBS += /usr/local/lib/libopencv_calib3d.so \
/usr/local/lib/libopencv_core.so \
/usr/local/lib/libopencv_features2d.so \
/usr/local/lib/libopencv_flann.so \
/usr/local/lib/libopencv_highgui.so \
/usr/local/lib/libopencv_imgcodecs.so \
/usr/local/lib/libopencv_imgproc.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_objdetect.so \
/usr/local/lib/libopencv_photo.so \
/usr/local/lib/libopencv_shape.so \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_superres.so \
/usr/local/lib/libopencv_videoio.so \
/usr/local/lib/libopencv_video.so \
/usr/local/lib/libopencv_videostab.so \
/usr/local/lib/libopencv_dnn.so \
/usr/local/lib/libopencv_dnn.so.3.3 \
/usr/local/lib/libopencv_dnn.so.3.3.0 \

INCLUDEPATH +=  /usr/include/python2.7\
                /usr/include/x86_64-linux-gnu/python2.7\
                -fno-strict-aliasing -Wdate-time -D_FORTIFY_SOURCE=2 -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes

LIBS += -L/usr/lib/python2.7/config-x86_64-linux-gnu -L/usr/lib -lpython2.7\
        -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

INCLUDEPATH += /home/guoyuechao/caffe-package/caffe/include\
                /home/guoyuechao/caffe-package/caffe/build/src

LIBS += -L/home/guoyuechao/caffe-package/caffe/build/lib

LIBS += -lcaffe

RESOURCES += \
    resource.qrc
