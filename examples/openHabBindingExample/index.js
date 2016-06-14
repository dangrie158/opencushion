"use strict";

const PORT = process.env.PORT || 80;
const SCLK_PIN = 7;
const DATA_PIN = 0;
const SEND_BINARY = '/sbin/send';
const RC_NETWORK_CODE = '11101';

const express = require('express');
const hx711 = require('hx711');
const bodyparser = require('body-parser');
const childProcess = require('child_process');

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

app.post('/switch/:id/:action', (req, res) => {
	var id = req.params.id;
	var action = req.params.action;

	var actionParam = action == 'on' ? '1' : '0';
	var idParam = '';

	switch(id){
	case 'A':
		idParam = '1';
	break;
	case 'B':
                idParam = '2';
        break;
	case 'C':
                idParam = '3';
        break;
	case 'D':
                idParam = '4';
        break;
	}
	
	var process = childProcess.spawn(SEND_BINARY, [RC_NETWORK_CODE, idParam, actionParam], {uid: 0});
	process.on('close', (code, signal) => {
		res.send(signal);
	});
});

app.listen(PORT, () => {
	console.log("app listening on port %s", PORT);
});
