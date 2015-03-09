/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      BackBone.cpp                                        **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/

#include "VCCMUI/BackBone.h"
#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

BackBone::BackBone() : m_t(0) , m_renderer(0)
{
   // connect the window changed signal to the quickwindows handler
  connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void BackBone::sync()
{
    if (!m_renderer) {
        m_renderer = new RenderState();
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setForward(m_forward);
}

void BackBone::quitclicked()
{

}

void BackBone::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }
}

void BackBone::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void BackBone::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void BackBone::MoveForward(qreal forward)
{
    if (forward == m_forward)
        return;
    m_forward = forward;
    emit fForward();
    if (window())
        window()->update();
}
