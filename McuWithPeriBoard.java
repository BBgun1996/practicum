package practicum;

import org.usb4java.Device;

public class McuWithPeriBoard extends McuBoard
{
    private static final byte RQ_GET_BUZZER    		= 1;
    private static final byte RQ_GET_VIBRATION    	= 2;
    private static final byte RQ_GET_GAS    		= 3;


    public McuWithPeriBoard(Device device) {
		super(device);
	}

    /**
     * Set status of LED on peripheral board
     * 
     * @param ledNo  the number of LED (0,1,2) to set status
     * @param value  status to set (0-off, 1-on)
     */
//    public void setLed(int ledNo, int value)
//    {
//        this.write(RQ_SET_LED, (short) ledNo, (short) value);
//    }
//
//    /**

    /**
     * Check the state of the switch
     * 
     * @return true when the switch is pressed; false otherwise
     */
    public boolean getBuzzer()
    {
        byte[] ret = this.read(RQ_GET_BUZZER, (short) 0, (short) 0);
//        System.out.printf("%d\n", ret[0]);
        return ret[0] == 1;
    }


    public boolean getVibrationWarning()
    {
    	byte[] ret = this.read(RQ_GET_VIBRATION, (short) 0, (short) 0);
//    	System.out.printf("%d\n", ret[0]);
        return ret[0] == 1;
    }
    
    public boolean getGasWarning()
    {
    	byte[] ret = this.read(RQ_GET_GAS, (short) 0, (short) 0);
//    	System.out.printf("%d\n", ret[0]);
        return ret[0] == 1;
    }
}
