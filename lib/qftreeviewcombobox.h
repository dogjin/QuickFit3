/*
    Copyright (c) 2008-2015 Jan W. Krieger (<jan@jkrieger.de>, <j.krieger@dkfz.de>), German Cancer Research Center (DKFZ) & IWR, University of Heidelberg

    

    This file is part of QuickFit 3 (http://www.dkfz.de/Macromol/quickfit).

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License (LGPL) as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License (LGPL) for more details.

    You should have received a copy of the GNU Lesser General Public License (LGPL)
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QFTREEVIEWCOMBOBOX_H
#define QFTREEVIEWCOMBOBOX_H

#include <QComboBox>
#include <QTreeView>
#include <QWidget>
#include <QModelIndex>
#include "lib_imexport.h"
#include "qfenhancedcombobox.h"

/*! \brief a QComboBox with a treeview as dropdown widget
    \ingroup tools_qt

    see <a href="http://www.qtcentre.org/threads/46078-Snippet-QComboBox-showing-tree-models">http://www.qtcentre.org/threads/46078-Snippet-QComboBox-showing-tree-models</a>

 */
class QFLIB_EXPORT QFTreeViewComboBox : public QFEnhancedComboBox {
        Q_OBJECT
    public:
        explicit QFTreeViewComboBox(QWidget *parent = 0);
        QVariant getCurrentIndexData(int role) const;
        void setCurrentFromModelData(const QVariant& data, int role=Qt::UserRole) ;
        virtual void showPopup();

    public slots:
        void selectIndex(const QModelIndex&index);

    protected slots:
        void indexSelected(const QModelIndex& idx);
    private:
        QTreeView* _treeView;
        QModelIndex currentItemIndex;
        bool setCurrentFromModelData(const QVariant& data, const QModelIndex &parent, int role=Qt::UserRole);

};

#endif // QFTREEVIEWCOMBOBOX_H
