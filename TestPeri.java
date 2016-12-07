package practicum;

import org.usb4java.Device;

public class TestPeri
{
    public static void main(String[] args) throws Exception
    {
        McuBoard.initUsb();

        try
        {
        	Device[] devices = McuBoard.findBoards();
        	
        	if (devices.length == 0) {
                System.out.format("** Practicum board not found **\n");
                return;
        	}
        	else {
                System.out.format("** Found %d practicum board(s) **\n", devices.length);
        	}
            McuWithPeriBoard peri = new McuWithPeriBoard(devices[0]);

            System.out.format("** Practicum board found **\n");
            System.out.format("** Manufacturer: %s\n", peri.getManufacturer());
            System.out.format("** Product: %s\n", peri.getProduct());

            while (true) 
            {
                Thread.sleep(500);

                boolean buzzerState = peri.getBuzzer();
                boolean vibrationWarning = peri.getVibrationWarning();
                boolean gasWarning = peri.getGasWarning();

                System.out.format("Buzzer state: %s | Vibration warning: %s | GAS warning: %s\n",
                        buzzerState, vibrationWarning, gasWarning);

            }
        }
        catch (Exception e)
        {
            System.out.println(e);
        }

        McuBoard.cleanupUsb();
    }
}
