﻿#ifndef QWTPLOTITEMDATAMODEL_H
#define QWTPLOTITEMDATAMODEL_H
#include "SAChartGlobals.h"
#include <QAbstractTableModel>
#include <QList>
#include <algorithm>
#include <vector>
#include <qwt_plot_item.h>
#include <limits>
class QwtPlotMultiBarChart;
#define QwtPlotItemDataModel_Use_Dynamic_Cast 0
///
/// \brief 显示item数据的tablemodel
///
class SA_CHART_EXPORT QwtPlotItemDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QwtPlotItemDataModel(QObject *p = 0);
    void setPlotItems(const QList<QwtPlotItem*>& items);
    void clear();
    void enableBackgroundColor(bool enable, int alpha = 30);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //nan的数值
    static double nan();
    //根据表格的列号获取对应的QwtPlotItem
    QwtPlotItem* getItemFromCol(int col, int *dataColumnDim = nullptr) const;
    //获取这个item对应的表格颜色
    QColor getItemColor(QwtPlotItem* item) const;
    //获取item对应的行数
    int getItemRowCount(QwtPlotItem* item) const;
    //获取item对应的第一个列号
    int getItemsColumnStartIndex(QwtPlotItem* item) const;
    //获取item对应的列范围
    void getItemColumnRange(QwtPlotItem* item,int* startCol=nullptr,int* endCol=nullptr) const;
public:
    //计算QwtPlotMultiBarChart的最大维度
    static int calcPlotMultiBarChartDim(const QwtPlotMultiBarChart* p);
    //获取绘图数据维度的描述
    virtual QString getItemDimDescribe(QwtPlotItem* item,int index) const;
protected:
    //获取item的最大行数
    virtual int calcItemDataRowCount(QwtPlotItem* item) const;
    //获取item的最大列数
    virtual int calcItemDataColumnCount(QwtPlotItem* item) const;
    //获取数据 row col 要对应item的维度
    virtual double getItemData(int row,int col,QwtPlotItem* item) const;
    //设置数据 row col 要对应item的维度
    virtual bool setItemData(int row,int col,QwtPlotItem* item,const QVariant& var);
private:
    //更新最大行数
    void updateMaxRow();
    void updateColumnCount();
    void updateItemColor();


    QString getItemNameFromCol(int col) const;

private:
    QList<QwtPlotItem*> m_items;
    QMap<QwtPlotItem*,int> m_itemsRowCount;
    QMap<QwtPlotItem*,QColor> m_itemsColor;///< 记录item的颜色，以免频繁读取
    QMap<QwtPlotItem*,int> m_itemsColumnStartIndex;///< 记录数据开始的那一列的索引
    int m_rowCount;
    bool m_enableBkColor;///< 是否允许背景色
    int m_bkAlpha;///< 背景透明度
    QMap<int,QPair<QwtPlotItem*,int> > m_columnMap;
};

#endif // QWTPLOTITEMDATAMODEL_H
