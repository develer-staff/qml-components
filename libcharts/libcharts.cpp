#include "libcharts.h"
#include <QtQuick/QSGVertexColorMaterial>
#include <QSGGeometryNode>
#include <QColor>

#define MINMAX(value, min, max) (value - min) / ((float)max - min)


Graph::Graph(QQuickItem *parent) : QQuickItem(parent) {
    setFlag(QQuickItem::ItemHasContents);
}

QSGGeometryNode *Graph::createNode() {
    auto node = new QSGGeometryNode();
    auto material = new QSGVertexColorMaterial();
    auto opaque = new QSGVertexColorMaterial();
    node->setMaterial(material);
    node->setOpaqueMaterial(opaque);
    node->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial | QSGNode::OwnsOpaqueMaterial);
    return node;
}

quint32 Graph::drawPointsInLines(QList<qreal> points, QSGGeometry::ColoredPoint2D *target, float point_size, QColor color, int target_index, int x_offset) {
    auto r = color.red(), g = color.green(), b = color.blue(), a = color.alpha();
    auto i = target_index, j = 0, w = 0;

    qreal h = height();
    if (points.length() == 1)
    {
        float x = (x_offset + w) * point_size;
        float y = h - (points.at(0) * h);
        target[i++].set(x, y, r, g, b, a);
        target[i++].set(x, y, r, g, b, a);
        j += 2;
    }
    else
    {
        foreach (auto point, points) {
            float x = (x_offset + w) * point_size;
            float y = h - (point * h);

            target[i++].set(x, y, r, g, b, a);
            j++;
            if (j % 2 == 0 && w < points.length() - 1) {
                target[i++].set(x, y, r, g, b, a);
                j++;
            }
            ++w;
        }
    }
    return j;
}

void Graph::updateGeometry(QSGGeometryNode *node, quint32 buffer_size) {
    auto geometry = new QSGGeometry(QSGGeometry::defaultAttributes_ColoredPoint2D(), buffer_size);
    node->setGeometry(geometry);
}

QSGNode *Graph::updatePaintNode(QSGNode *old, UpdatePaintNodeData *update) {
    Q_UNUSED(update);

    auto node = static_cast<QSGGeometryNode *>(old);

    if (!node)
        node = createNode();
    updateGeometry(node, bufferSize());

    auto geometry = node->geometry();
    drawGeometry(geometry);
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}


LineChart::LineChart(QQuickItem *parent) : Graph(parent)
{
    model = 0;
    line_width = 1;
    color = Qt::black;
    connect(this, SIGNAL(colorChanged()), SLOT(update()));
    connect(this, SIGNAL(lineWidthChanged()), SLOT(update()));
}

LineSeries *LineChart::getModel() const
{
    return model;
}

void LineChart::setModel(LineSeries *val)
{
    if (val != model)
    {
        if (model)
            model->disconnect(this);
        model = val;
        connect(model, SIGNAL(graphModelChanged(QList<qreal>)), SLOT(update()));
        emit modelChanged();
        update();
    }
}

quint32 LineChart::bufferSize()
{
    return (model->graphModel().size() - 1) * 2;
}

void LineChart::drawGeometry(QSGGeometry *geometry)
{
    geometry->setDrawingMode(GL_LINES);
    geometry->setLineWidth(line_width);
    auto points = geometry->vertexDataAsColoredPoint2D();
    drawPointsInLines(model->graphModel(), points, width() / (model->graphModel().size() - 1), color);
}


LineSeries::LineSeries(QObject *parent) : QObject(parent)
{
    scale_minimum = 0;
    scale_maximum = 100;
    connect(this, SIGNAL(dataSourceChanged(QList<qreal>)), SLOT(updateGraphModel()));
}

QList<qreal> LineSeries::graphModel() const
{
    return graph_model;
}

void LineSeries::updateGraphModel()
{
    graph_model.clear();
    for (auto p : data_source)
        graph_model << MINMAX(p, scale_minimum, scale_maximum);
    emit graphModelChanged(graph_model);
}
