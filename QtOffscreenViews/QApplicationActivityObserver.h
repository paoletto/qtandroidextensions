/*
  Offscreen Android Views library for Qt

  Author:
  Sergey A. Galin <sergey.galin@gmail.com>

  Distrbuted under The BSD License

  Copyright (c) 2014, DoubleGIS, LLC.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  * Neither the name of the DoubleGIS, LLC nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#include <QScopedPointer>
#include <QMutex>
#include <QObject>

/*!
 * A place where various QObjects can connect to receive signals about
 * application activation and deactivation. It's a shame that QApplication does not
 * implement such signals...
 * Please note that for this to work you the application should implement calling
 * to setApplicationActive(). For QWidget / QGraphicsWidget based application this
 * can be done in the main window, protected virtual bool event(QEvent *e),
 * the events types are QEvent::WindowActivate and QEvent::WindowDeactivate.
 * If you do not implement the calls some functionality which relies on the
 * applicationActiveStateChanged() may not work.
 */
class QApplicationActivityObserver: public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool applicationActive READ isApplicationActive WRITE setApplicationActive)
private:
	QApplicationActivityObserver(): is_active_(true) {}

public:
	static QApplicationActivityObserver * instance();

	bool isApplicationActive() const { return is_active_; }

	static void installQApplicationEventFilter();

public slots:
	/*!
	 * Sets activity flag and emits applicationActive; this function
	 * is usually called from main window.
	 */
	void setApplicationActive(bool active);

signals:
	void applicationActiveStateChanged();

protected:
	bool eventFilter(QObject * obj, QEvent * event);

private:
	volatile bool is_active_;
	Q_DISABLE_COPY(QApplicationActivityObserver)
};

