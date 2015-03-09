/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      BackBone.h                                          **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/
#ifndef BackBone_H
#define BackBone_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include "VCCMStates/RenderState.h"

class BackBone : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
    Q_PROPERTY(qreal forward READ forward WRITE MoveForward NOTIFY fForward)
public:
    BackBone();
    qreal t() const { return m_t; }
    qreal forward() const { return m_forward; }
    void setT(qreal t);
    void MoveForward(qreal forward);

signals:
    void tChanged();
    void fForward();
public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);
    void quitclicked();

private:
    qreal m_t,m_forward;
    RenderState *m_renderer;
};

#endif // BackBone_H
