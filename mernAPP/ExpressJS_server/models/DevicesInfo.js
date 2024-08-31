const { Schema, model } = require('mongoose')

const deviceInfoSchema = new Schema({
    identifier:{
        type: Number,
    },
    name:{
        type: String,
    },
    status:{
        type: Boolean,
    }
})

const deviceInfoModel = model('DeviceInfo', deviceInfoSchema, 'devicesInfo')

module.exports = deviceInfoModel