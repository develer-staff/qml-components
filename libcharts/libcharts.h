#ifndef LIBCHARTS_H
#define LIBCHARTS_H

#include <QQuickItem>
#include <QSGGeometry>

class QSGGeometryNode;
class LineSeries;

class Graph : public QQuickItem {
friend class TestGraph;
    Q_OBJECT
    Q_DISABLE_COPY(Graph)
public:
    explicit Graph(QQuickItem *parent=0);
protected:
    QSGGeometryNode *createNode();
    quint32 drawPointsInLines(QList<qreal> points, QSGGeometry::ColoredPoint2D *target, float point_size, QColor color, int start=0, int x_offset=0);
    void updateGeometry(QSGGeometryNode *node, quint32 buffer_size);
    virtual QSGNode *updatePaintNode(QSGNode *old, UpdatePaintNodeData *update);
private:
    virtual quint32 bufferSize() = 0;
    virtual void drawGeometry(QSGGeometry *geometry) = 0;
};

class LineChart : public Graph {
    Q_OBJECT
    Q_PROPERTY(LineSeries *model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QColor color MEMBER color NOTIFY colorChanged)
    Q_PROPERTY(qreal lineWidth MEMBER line_width NOTIFY lineWidthChanged)

public:
    LineChart(QQuickItem *parent = 0);
    LineSeries *getModel() const;
    void setModel(LineSeries *val);

signals:
    void modelChanged();
    void colorChanged();
    void lineWidthChanged();

private:
    virtual quint32 bufferSize() override;
    virtual void drawGeometry(QSGGeometry *geometry) override;
    LineSeries *model;
    QColor color;
    qreal line_width;
};


class LineSeries : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<qreal> dataSource MEMBER data_source NOTIFY dataSourceChanged)
	Q_PROPERTY(qreal scaleMaximum MEMBER scale_maximum NOTIFY scaleMaximumChanged)
	Q_PROPERTY(qreal scaleMinimum MEMBER scale_minimum NOTIFY scaleMinimumChanged)

public:
    LineSeries(QObject *parent = 0);
    QList<qreal> graphModel() const;

signals:
    void graphModelChanged(QList<qreal> val);
    void dataSourceChanged(QList<qreal> val);
	void scaleMaximumChanged(qreal);
	void scaleMinimumChanged(qreal);

private slots:
    void updateGraphModel();

private:
    QList<qreal> data_source, graph_model;
    qreal scale_maximum, scale_minimum;
};

#endif // LIBCHARTS_H

