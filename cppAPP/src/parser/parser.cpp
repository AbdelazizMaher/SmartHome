#include "parser.hpp"

namespace sh {

/** Method to log the details of devices */
void parser::log(std::vector<devices> &dev)
{
    /** Iterate over each device in the vector */
    for (auto &element : dev)
    {
        std::cout << "Device ID: " << element._id << std::endl;
        std::cout << "Device Identifier: " << element.identifier << std::endl;
        std::cout << "Device Name: " << element.name << std::endl;
        std::cout << "Device Status: " << element.status << std::endl;
        std::cout << "Device __v: " << element.__v << std::endl;
    }
}

/** Method to parse JSON string into vector of devices struct */
std::vector<devices> parser::parse(const std::string &msg)
{
    /** Vector to hold the parsed devices */
    std::vector<devices> deviceData;

    /** Check if the input message is empty and return an empty vector if empty */
    if (msg.empty())
        return deviceData; 

    try
    {
        /** Wrap the JSON string in a JSON object with a "data" field */
        std::string wrappedJsonString = "{ \"data\":" + msg + "}";

        /** Parse JSON string into a nlohmann::json object */
        nlohmann::json jsonData = nlohmann::json::parse(wrappedJsonString);

        /** Check if the "data" field exists and is an array */
        if (!jsonData.contains("data") || !jsonData["data"].is_array())
        {
            /** Log error if "data" field is missing or not an array */
            std::cerr << "\"data\" field is missing or not an array" << std::endl;
            return deviceData; 
        }

        /** Iterate over each item in the "data" array */
        for (const auto &item : jsonData["data"])
        {
            /** Parse each item into a device struct */
            devices device = parse_device(item);
            /** Add the device to the vector */
            deviceData.push_back(device);
        }
    }
    catch (const nlohmann::json::exception &e)
    {
        /** Log JSON parsing error and return the empty vector in case of an error */
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return deviceData; 
    }

    /** Return the vector of parsed devices */
    return deviceData;
}

/** Method to convert JSON object to devices struct */
devices parser::parse_device(const nlohmann::json &jsonData)
{
    /** Create a new devices struct */
    devices device;

    /** Extract fields from JSON object and assign to the devices struct */
    jsonData.at("_id").get_to(device._id);
    jsonData.at("identifier").get_to(device.identifier);
    jsonData.at("name").get_to(device.name);
    jsonData.at("status").get_to(device.status);
    jsonData.at("__v").get_to(device.__v);

    /** Return the populated devices struct */
    return device;
}

} // namespace sh
