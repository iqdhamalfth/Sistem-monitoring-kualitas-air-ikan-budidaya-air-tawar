void nilaiPH(){
  nilai_analog_PH = analogRead(ph_Pin);
  Serial.print("Nilai ADC Ph: ");
  Serial.println(nilai_analog_PH);
  TeganganPh = 5 / 1024.0 * nilai_analog_PH;
  Serial.print("TeganganPh: ");
  Serial.println(TeganganPh, 3);

  PH_step = (PH4 - PH7) / 3;
  Po = 7.00 + ((PH7 - TeganganPh) / PH_step);
  Serial.print("Nilai PH cairan: ");
  Serial.println(Po, 2);
  delay(1000);
}
