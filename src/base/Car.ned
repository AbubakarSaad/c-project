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

package globcomm.src.base;


import org.car2x.veins.base.modules.IBaseApplLayer;
import org.car2x.veins.modules.nic.Nic80211p;
import org.car2x.veins.modules.mobility.traci.TraCIMobility;


module Car
{
	parameters:
	    @display("i=device/laptop_l");
	    string applicationModule;
	gates:
	    input radioIn; // gate for sendDirect
	    
	submodules:
	    appl: <applicationModule> like IBaseApplLayer {
	    	@display("p=90,35;b=100,20,react");
	    }
	    
	    nic: Nic80211p {
	    	@display("p=90,35;b=100,20,react");
	    }
	    
	    mobility: TraCIMobility {
	    	@display("p=257,172;i=block/cogwheel");
	    }
	    
	    
	  
	connections:
	    nic.upperLayerOut --> appl.lowerLayerIn;
	    nic.upperLayerIn <-- appl.lowerLayerOut;
	    nic.upperControlOut --> appl.lowerControlIn;
	    nic.upperControlIn <-- appl.lowerControlOut;
	    
	    
	    radioIn --> nic.radioIn;

}