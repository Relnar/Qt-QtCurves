#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
: QWidget(parent)
, mBackgroundColor(0, 0, 255)
, mShapeColor(255, 255, 255)
, mShape(Astroid)
, mStepCount(256)
, mScale(40.0f)
, mIntervalLength(2 * M_PI)
{
    mPen.setWidth(2);
    mPen.setColor(mShapeColor);
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

void RenderArea::on_shape_changed()
{
    switch (mShape)
    {
        case Astroid:
            mScale = 90;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
            break;
        case Cycloid:
            mScale = 10;
            mIntervalLength = 4 * M_PI;
            mStepCount = 128;
            break;
        case HuygenCycloid:
            mScale = 12;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
            break;
        case HypoCycloid:
            mScale = 40;
            mIntervalLength = 2 * M_PI;
            mStepCount = 256;
            break;
        case Line:
            mScale = 100;
            mIntervalLength = 2.0f;
            mStepCount = 128;
            break;
        case Circle:
            mScale = 100;
            mIntervalLength = 2 * M_PI;
            mStepCount = 128;
            break;
        default:
            break;
    }
}

QPointF RenderArea::compute(float t)
{
    switch (mShape)
    {
        case Astroid:
            return compute_astroid(t);
        case Cycloid:
            return compute_cycloid(t);
        case HuygenCycloid:
            return compute_huygens_cycloid(t);
        case HypoCycloid:
            return compute_hypo_cycloid(t);
        case Line:
            return compute_line(t);
        case Circle:
            return compute_circle(t);
        default:
            return QPointF(0, 0);
    }
}
QPointF RenderArea::compute_astroid(float t)
{
    return QPointF(2.0f * pow(cos(t), 3.0f),
                   2.0f * pow(sin(t), 3.0f));
}

QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(1.5f * (1.0f - cos(t)),
                   1.5f * (t - sin(t)));
}

QPointF RenderArea::compute_huygens_cycloid(float t)
{
    return QPointF(4.0f * (3 * cos(t) - cos(3 * t)),
                   4.0f * (3 * sin(t) - sin(3 * t)));
}

QPointF RenderArea::compute_hypo_cycloid(float t)
{
    return QPointF(1.5f * (2 * cos(t) + cos(2 * t)),
                   1.5f * (2 * sin(t) - sin(2 * t)));
}

QPointF RenderArea::compute_line(float t)
{
    return QPointF(1.0f - t, 1.0f - t);
}

QPointF RenderArea::compute_circle(float t)
{
    return QPointF(cos(t), sin(t));
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(mBackgroundColor);
    painter.setPen(mPen);

    painter.drawRect(rect());

    QPoint center = rect().center();
    float step = mIntervalLength / mStepCount;

    QPointF point = compute(0);
    QPoint previousPixel(point.x() * mScale + center.x(),
                         point.y() * mScale + center.y());
    for (float t = step; t <= mIntervalLength; t += step)
    {
        point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());
        painter.drawLine(pixel, previousPixel);
        previousPixel = pixel;
    }

    point = compute(mIntervalLength);

    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());
    painter.drawLine(pixel, previousPixel);
    previousPixel = pixel;
}
