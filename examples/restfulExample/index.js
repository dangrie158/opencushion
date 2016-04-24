"use strict";

const PORT = process.env.PORT || 80;
const SCLK_PIN = 7;
const DATA_PIN = 0;

const express = require('express');
const hx711 = require('hx711');
const bodyparser = require('body-parser');

const app = express();
const sensor = new hx711(SCLK_PIN, DATA_PIN);

let scale = 8000;

sensor.tare();
sensor.setScale(8000);

app.use(bodyparser.json());

app.get('/', (req, res) => {
	res.json({
		value: sensor.getUnits(),
		scale: sensor.getScale(),
		offset: sensor.getOffset()
	});
});

app.get('/units', (req, res) => {
	res.json(sensor.getUnits());
});

app.get('/offset', (req, res) => { 
        res.json(sensor.getOffset());
});

app.get('/scale', (req, res) => { 
        res.json(sensor.getScale());
});

app.put('/scale', (req, res) => {
	var newScale = req.body;
	sensor.setScale(newScale);
	res.json(hx711.getScale());	
});

app.put('/offset', (req, res) => {
        var newOffset = req.body; 
        sensor.setOffset(newOffset);
        res.json(hx711.getOffset());
});

app.post('/tare', (req, res) => {
        sensor.tare();
        res.json({
                value: sensor.getUnits(),
                scale: sensor.getScale(),
                offset: sensor.getOffset()
        });
});

app.listen(PORT, () => {
	console.log("app listening on port %s", PORT);
});
