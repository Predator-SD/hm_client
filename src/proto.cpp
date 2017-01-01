#include <qdebug.h>

#include "proto.h"
//#include "ui_mainwindow.h"

Proto::Proto()
{
}

Proto::~Proto()
{
}

int Proto::add(char **dst, const char *maxdst, const void *src, const int nsrc)
{

    char *start;

    if(maxdst < *dst + nsrc + sizeof(nsrc)) {
        qDebug() << "pair too long";
        exit(0);
        return -1;
    }

    start = *dst;

    qDebug() << "written0 " << (*dst - start);

    memcpy(*dst, &nsrc, sizeof(nsrc));
    *dst += sizeof(nsrc);

    qDebug() << "written1 " << (*dst - start);
    memcpy(*dst, src, nsrc);
    *dst += nsrc;

    qDebug() << "whearthmodritten2 " << (*dst - start);

    return (*dst - start);


}

int Proto::packet(char *dst, enum packet_e packet, char *src, const int nsrc)
{
    int len;
    int magic = 0xffffffff;

    len = 3 * sizeof(packet) + nsrc;

    memcpy(dst, &magic, sizeof(magic));
    dst += sizeof(magic);

    memcpy(dst, &packet, sizeof(packet));
    dst += sizeof(packet);

    memcpy(dst, &len, sizeof(len));
    dst += sizeof(len);

    memcpy(dst, src, nsrc);
    dst += nsrc;

    return len;
}
/*
QMap Proto::read(char *src, const int nsrc)
{

    QMap<QString, QString> map;
    enum packet_e t;
    char *tmp;

    if(nsrc < 16) {
        return P_NONE;
    }

    t = (enum packet_e)(*(int *)(src + sizeof(int)));

    start = src + 2*(sizeof(int));
    end = start + nsrc;

    while(start < end) {
        if(t == P_LOGIN) {
            map['error'] = src;
        }
    }

}
*/
