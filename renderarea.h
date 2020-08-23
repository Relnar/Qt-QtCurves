#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    enum ShapeType
    {
        Astroid,
        Cycloid,
        HuygenCycloid,
        HypoCycloid,
        Line,
        Circle,
        LastShape
    };

    void setBackgroundColor(const QColor& color) { mBackgroundColor = color; }
    const QColor& backgroundColor() const { return mBackgroundColor; }

    void setLineColor(const QColor& color) { mShapeColor = color; mPen.setColor(color); }
    const QColor& lineColor() const { return mShapeColor; }

    void setShape(ShapeType shape) { mShape = shape; on_shape_changed(); }
    ShapeType shape() const { return mShape; }

    void setScale(float scale) { mScale = scale; }
    float scale() const { return mScale; }

    void setIntervalLength(float length) { mIntervalLength = length; }
    float intervalLength() const { return mIntervalLength; }

    void setStepCount(int stepCount) { mStepCount = stepCount; }
    int stepCount() const { return mStepCount; }

    QPointF compute(float t);

protected:
    void paintEvent(QPaintEvent *event) override;

signals:

private:
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens_cycloid(float t);
    QPointF compute_hypo_cycloid(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);
    void on_shape_changed();

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    QPen mPen;
    ShapeType mShape;

    int mStepCount;
    float mScale;
    float mIntervalLength;
};

#endif // RENDERAREA_H
