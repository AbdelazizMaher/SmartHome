// Import required modules
const express = require('express');                // Express framework for handling HTTP requests
const mongoose = require('mongoose');              // Mongoose for MongoDB interaction
const deviceInfoModel = require('./models/DevicesInfo'); // Import the DeviceInfo model
const cors = require('cors');                      // CORS middleware to allow cross-origin requests

// Initialize the Express application
const app = express();

// Middleware setup
app.use(cors());                                   // Enable CORS for all routes
app.use(express.json());                           // Parse incoming JSON requests

// Retrieve environment variables for database connection
const username = process.env.USERNAME,
      password = process.env.PASSWORD,
      database = process.env.DB;

// Connect to MongoDB using Mongoose
mongoose.connect(
    `mongodb+srv://${username}:${password}@smarthome.8afsnyz.mongodb.net/${database}?retryWrites=true&w=majority&appName=SmartHome`
);

// Route to retrieve all device information
app.get("/devicesInfos", async (req, res) => {
    try {
        // Fetch all devices from the database
        const devices = await deviceInfoModel.find();
        // Respond with the retrieved devices in JSON format
        res.json(devices);
    } catch (err) {
        // Log any errors and respond with a server error status
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Route to add a new device
app.post("/addDevice", async (req, res) => {
    try {
        // Create a new device instance using the request body data
        const newDevice = new deviceInfoModel(req.body);
        // Save the new device to the database
        await newDevice.save();
        // Respond with the saved device data
        res.json(req.body);
    } catch (err) {
        // Log any errors and respond with a server error status
        console.error(err);
        res.status(500).json({ error: 'Server error' });
    }
});

// Route to toggle the status of a specific device by identifier
app.get("/Led/:identifier", async (req, res) => {
    // Extract the identifier parameter from the request
    const { identifier } = req.params;
    const { body } = req.body;
    console.log(identifier, body);

    try {
        // Find the device in the database by its identifier
        const device = await deviceInfoModel.findOne({ identifier: identifier });

        // If the device is not found, respond with a 404 error
        if (!device) {
            return res.status(404).json({ error: "Device not found" });
        }

        // Toggle the device status between true (on) and false (off)
        device.status = !device.status;
        // Save the updated device back to the database
        await device.save();

        // Fetch all devices again to return updated information
        const devices = await deviceInfoModel.find();
        // Respond with the updated list of devices
        res.json({ devices });
    } catch (err) {
        // Log any errors and respond with a server error status
        console.error(err);
        res.status(500).json({ error: "Server error" });
    }
});

// Start the server and listen on port 3001
app.listen("3001", () => {
    console.log("Server is running on port 3001!");
});
