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

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.modules.mobility.traci.TraCIScenarioManagerLaunchd;


network Connectivity
{
	parameters:
	    @display("i=background/green");
	    int numberRSU = default(0);

	submodules:
	    rsu[numberRSU]: RSU;
	    
	    baseWorldUtility: BaseWorldUtility {
	    	@display("p=70,20");
	    }
	    
	    connectionManager: ConnectionManager {
	    	@display("p=70,91");
	    }
	    
	    manager: TraCIScenarioManagerLaunchd {
	    	@display("p=512, 128");
	    }
	    
	    
	connections allowunconnected:
	    

}