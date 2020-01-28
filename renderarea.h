#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    enum ShapeType {Astroid, Cycloid,
                 HuygensCycloid, HypoCycloid};

    void SetBackgroundColor(QColor color) { mBackgroundColor = color; }
    QColor GetBackgroundColor() const { return mBackgroundColor; }

    void SetShape(ShapeType shape) { mShape = shape; }
    ShapeType GetShape() const {return mShape; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor mBackgroundColor;
    QColor mShapeColor;
    ShapeType mShape;

signals:

};

#endif // RENDERAREA_H
