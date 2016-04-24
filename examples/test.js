const hx711 = require('../hx711');
const SCLK = 7;
const DATA = 0;

var sensor = hx711(SCLK, DATA);
sensor.tare();
sensor.setScale(5000);
while(true){
	console.log(sensor.getUnits());
}
