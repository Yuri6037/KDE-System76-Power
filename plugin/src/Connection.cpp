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

#include <QtDBus/QDBusMessage>
#include "Connection.hpp"

Connection::Connection(QObject *parent)
    : QObject(parent)
    , _connection(QDBusConnection::systemBus())
    , _curProfile(PowerProfile_Balanced)
{
    _connection.connect(DBUS_SERVICE, DBUS_PATH, DBUS_INTERFACE, "PowerProfileSwitch", this, SLOT(onProfileChanged()));
}

void Connection::setProfile(Connection::PowerProfile profile)
{
    QDBusMessage msg;
    switch (profile) {
        case Connection::PowerProfile::PowerProfile_Balanced:
            msg = QDBusMessage::createMethodCall(DBUS_SERVICE, DBUS_PATH, DBUS_INTERFACE, "Balanced");
            break;
        case Connection::PowerProfile::PowerProfile_Battery:
            msg = QDBusMessage::createMethodCall(DBUS_SERVICE, DBUS_PATH, DBUS_INTERFACE, "Battery");
            break;
        case Connection::PowerProfile::PowerProfile_Performance:
            msg = QDBusMessage::createMethodCall(DBUS_SERVICE, DBUS_PATH, DBUS_INTERFACE, "Performance");
            break;
    }
    _connection.call(msg);
}

Connection::PowerProfile Connection::getProfile()
{
    return _curProfile;
}

void Connection::onProfileChanged(const QString &name)
{
    if (name == "Performance") {
        _curProfile = PowerProfile_Performance;
    } else if (name == "Balanced") {
        _curProfile = PowerProfile_Balanced;
    } else if (name == "Battery") {
        _curProfile = PowerProfile_Battery;
    }
    emit powerProfileChanged();
}
