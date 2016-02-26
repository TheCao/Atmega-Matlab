clear all;
close all;
clc;
instrreset;
y=zeros(1,100); %stworzenie tablicy o jednym wierszu i 100 kolumach
z = ' ';
serial_port_object = serial('COM16');
serial_port_object.Terminator = '';
serial_port_object.Timeout = 100;
serial_port_object.InputBufferSize = 1;
serial_port_object.BaudRate = 9600;
 
fopen(serial_port_object);
 
 
i=1;
 
 
figure('Name','Serial communication: Matlab + ATMega32')
title('SERIAL COMMUNICATION MATLAB + ATMega32');
xlabel('Numer próbki');
ylabel('Wartoœæ');
grid on;
hold on;
 
 
while i<=1000
        %disp(['Przebieg nr: ',num2str(i)]);
        ylim([0 700]); %ustawiaj¹ limity osi
        xlim([0 i+5]);

 
       wartosc_pomiaru = fscanf(serial_port_object)'; 
       %disp(['Pobrana wartoœæ: ',num2str(wartosc_pomiaru)]);
       if wartosc_pomiaru ~= ';'
           z=strcat(z,wartosc_pomiaru);
             %disp(['Aktualne z: ',num2str(z)]);
       elseif z == ' '
               continue;
       else
            
            z = str2double(z);
            y(i)=(z);
            z = '';
            plot(i,y(i),'o-r'); 
            drawnow
            i=i+1;
       end
end
 
 
fclose(serial_port_object);
delete(serial_port_object);
