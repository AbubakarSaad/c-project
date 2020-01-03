//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package globcomm.src;

import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

simple MyThesisApp extends DemoBaseApplLayer
{
    parameters:
//        @statistic[messagesTransmitted](record=sum);
//        @statistic[messageDelay](record=sum);
//        @statistic[messagesReceived](record=sum);
//        @statistic[isInROI](record=sum);
//        @statistic[direction](record=last);
        
        // Time interval to delete out-dated received beacons
        double beaconEntryTTL @unit(s) = default(3s);
        
        // Broadcast Supression parameters
        int numberTimeSlots = default(4);
        double avgCommRange @unit(m) = default(500m);
        double estimatedOneHopDelay @unit(s) = default(60ms);
        double maxDelay @unit(s) = default(4ms);
        
        
        // Sender-based Broadcast Suppression Parameters
        double minDistance @unit(m) = default(0m);
        double maxDistance @unit(m) = default(500m);
        
        double maxGPSError @unit(m) = default(0m);
        
        double datarate @unit(bps);
        
   		@class(veins::MyThesisApp);
    
}
