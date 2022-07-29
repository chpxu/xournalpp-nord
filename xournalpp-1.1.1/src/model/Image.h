/*
 * Xournal++
 *
 * An Image on the document
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <string>
#include <vector>

#include "Element.h"


class Image: public Element {
public:
    Image();
    virtual ~Image();

public:
    void setWidth(double width);
    void setHeight(double height);

    void setImage(std::string data);
    void setImage(cairo_surface_t* image);
    void setImage(GdkPixbuf* img);
    cairo_surface_t* getImage();

    virtual void scale(double x0, double y0, double fx, double fy, double rotation, bool restoreLineWidth);
    virtual void rotate(double x0, double y0, double th);

    /**
     * @overwrite
     */
    virtual Element* clone();

public:
    // Serialize interface
    void serialize(ObjectOutputStream& out) const override;
    void readSerialized(ObjectInputStream& in) override;

private:
    void calcSize() const override;

    static cairo_status_t cairoReadFunction(Image* image, unsigned char* data, unsigned int length);

private:
    cairo_surface_t* image = nullptr;

    std::string data;

    std::string::size_type read = false;
};
