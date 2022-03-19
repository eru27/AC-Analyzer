
struct sample_packet
{
  uint32_t magic;
  uint16_t  val_array[6];
} __attribute__((packed));

sample_packet pack;

// the setup routine runs once when you press reset:
void setup() {
  pack.magic = 0x00FFFFFF;
  
  Serial.begin(115200);
  //Serial.println(sizeof(sample_packet));
}


// the loop routine runs over and over again forever:
void loop() {
 uint16_t a = 0;
  
  for (int i = 0; i < 6; ++i)
  {
    a = analogRead(A0);
    pack.val_array[i] = a;
  }

  uint8_t* pack_pointer = (uint8_t*) &pack;

  Serial.write(pack_pointer, sizeof(sample_packet));
  
  //Serial.write(0xFF);
  //Serial.write(0xFF);
  //Serial.write(0xFF);
  //Serial.write(0x00);
  
  delay(200);
}
