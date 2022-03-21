
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

  pack.val_array[0] = analogRead(A0);
  pack.val_array[1] = analogRead(A1);
  pack.val_array[2] = analogRead(A2);
  pack.val_array[3] = analogRead(A3);
  pack.val_array[4] = analogRead(A4);
  pack.val_array[5] = analogRead(A5);

  uint8_t* pack_pointer = (uint8_t*) &pack;

  Serial.write(pack_pointer, sizeof(sample_packet));
  
  delay(200);
}
