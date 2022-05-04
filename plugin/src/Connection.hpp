// Copyright (c) 2022, Yuri6037
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// * Neither the name of time-tz nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <QtCore/QtPlugin>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>

#include "system76_power_kde_plugin_export.h"

#define DBUS_INTERFACE "com.system76.PowerDaemon"
#define DBUS_PATH "/com/system76/PowerDaemon"
#define DBUS_SERVICE "com.system76.PowerDaemon"

class SYSTEM76_POWER_KDE_PLUGIN_EXPORT Connection : public QObject {
Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    enum PowerProfile {
        PowerProfile_Performance,
        PowerProfile_Balanced,
        PowerProfile_Battery
    };
    Q_ENUM(PowerProfile)

    Q_INVOKABLE void setProfile(Connection::PowerProfile profile);
    Q_INVOKABLE Connection::PowerProfile getProfile();

signals:
    void powerProfileChanged() const;

private slots:
    void onProfileChanged(const QString &profile);

private:
    QDBusConnection _connection;
    PowerProfile _curProfile;
};
