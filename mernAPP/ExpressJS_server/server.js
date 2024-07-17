const express = require('express')              
const mongoose = require('mongoose')
const deviceInfoModel = require('./models/DevicesInfo')
const cors = require('cors')

const app = express()
app.use(cors())
app.use(express.json())

const   username = process.env.USERNAME,
        password = process.env.PASSWORD,
        database = process.env.DB;

mongoose.connect(
    `mongodb+srv://${username}:${password}@smarthome.8afsnyz.mongodb.net/${database}?retryWrites=true&w=majority&appName=SmartHome`
)

app.get("/devicesInfos", async (req,res)=> {
    try {
        const devices = await deviceInfoModel.find();
        res.json(devices);
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
})

app.post("/addDevice",async(req,res)=>{
    try {
        const newDevice = new deviceInfoModel(req.body);
        await newDevice.save();
        res.json(req.body)
    } catch (err) {
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
})

app.listen("3001", ()=> {
    console.log("server works now!!");
})