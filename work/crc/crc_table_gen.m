POLYNOMIAL = 0x1D;

fid = fopen('crc_header.h', 'w');

fprintf(fid, '#include <stdint.h>\n\n');
fprintf(fid, 'static const uint8_t CRC8_J1850_E2E_TABLE[256] = \n');
fprintf(fid, '{\n\t');
k = 0;
for message_byte = 0x00:0xFF
    
    % Get the next byte
    remainder = message_byte;
    
    % Perform modulo-2 division, a bit at a time, for this byte
    for bit = 1:8
        
        if(bitand(uint8(remainder),0x80) ~= 0)
            remainder = bitxor(bitshift(remainder,1),POLYNOMIAL);
        else
            remainder = bitshift(uint8(remainder), 1);
        end
        
    end
    
    if(mod(k,8) == 0 && k > 0)
        fprintf(fid, '\n\t');
    end
    
    if(message_byte == 0xFF)
        fprintf(fid, '0x%02X\n};', remainder);
    else
        fprintf(fid, '0x%02X, ', remainder);
        k = k+1;
    end
    
end

fclose(fid);