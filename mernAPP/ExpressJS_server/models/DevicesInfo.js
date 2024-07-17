const { Schema, model } = require('mongoose')

const deviceInfoSchema = new Schema({
    identifier:{
        type: String,
    },
    name:{
        type: String,
    },
    status:{
        type: String,
    }
})

const deviceInfoModel = model('DeviceInfo', deviceInfoSchema, 'devicesInfo')

module.exports = deviceInfoModel