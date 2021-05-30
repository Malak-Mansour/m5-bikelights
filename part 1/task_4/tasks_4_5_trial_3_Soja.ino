case 3:
          {
            float ax, ay, az = 0;
            float ax_avg, ay_avg, az_avg = 0;
           
            M5.imu.getAccel(&ax, &ay, &az);
           int n = sizeof(ax);
            ax_avg = ax/n;
            ay_avg = ay/n;
            az_avg = az/n;
            //now calculate the moving average
             ax_avg = ((ax_avg * (n - 1)) + fabs(ax)) / n;
            ay_avg = ((ay_avg * (n - 1)) + fabs(ay)) / n;
            az_avg = ((az_avg * (n - 1)) + fabs(az)) / n;

            if (ax_avg>=thresh || ay_avg>=thresh || az_avg>=thresh)
            {
               while (FSM==3)
                   {
                      setBuff(0x00, 0x00, 0x00); // red state
                      M5.dis.displaybuff(DisBuff); // display the state
                      delay(500); // delay the off state for 0.5 second
                      setBuff(0xff, 0x00, 0x00); // set state of color to red
                      M5.dis.displaybuff(DisBuff); // display the state
                      delay(500);// delay for 0.5 second
                      M5.update(); // update the state of the board
                     
                   }
              }
              else
              {
                setBuff(0xff, 0xff, 0xff); // set state of color to white
                M5.dis.displaybuff(DisBuff);
