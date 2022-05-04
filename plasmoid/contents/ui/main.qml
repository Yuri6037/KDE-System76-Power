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

import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Controls 1.4

import system76_power_kde 0.1

Item {
    function getProfileName() {
        switch (con.getProfile()) {
            case 0:
                return "Performance";
            case 1:
                return "Balanced";
            case 2:
                return "Battery";
        }
    }

    property string currentProfileText: "Current profile: " + getProfileName();
    property bool performance: con.getProfile() == 0;
    property bool balanced: con.getProfile() == 1;
    property bool battery: con.getProfile() == 2;

    Connection {
        id: con;
        onPowerProfileChanged: {
            currentProfileText = "Current profile: " + getProfileName();
            switch (con.getProfile()) {
                case 0:
                    performance = true;
                    balanced = false;
                    battery = false;
                    break;
                case 1:
                    performance = false;
                    balanced = true;
                    battery = false;
                    break;
                case 2:
                    performance = false;
                    balanced = false;
                    battery = true;
                    break;
            }
        }
    }

    Plasmoid.fullRepresentation: ColumnLayout {
        PlasmaComponents.Label {
            text: currentProfileText;
            color: "black";
        }
        ExclusiveGroup { id: selectedProfile }
        PlasmaComponents.RadioButton {
            text: "Performance";
            checked: performance;
            exclusiveGroup: selectedProfile;
            onClicked: con.setProfile(0);
        }
        PlasmaComponents.RadioButton {
            text: "Balanced";
            checked: balanced;
            exclusiveGroup: selectedProfile;
            onClicked: con.setProfile(1);
        }
        PlasmaComponents.RadioButton {
            text: "Battery";
            checked: battery;
            exclusiveGroup: selectedProfile;
            onClicked: con.setProfile(2);
        }
    }
}
