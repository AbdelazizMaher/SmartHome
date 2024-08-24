import {  useRef, useState, useEffect } from "react";
import Axios from "axios";

import DeviceTag from './DeviceTag';
import "./DeviceForm.css";

export default function DeviceForm() {
    const identifier = useRef();
    const name = useRef();
  
    const [devices, setDevices] = useState([])

    // useEffect to fetch device information when the component mounts or when devices array changes
    useEffect(()=> {
      Axios.get("http://localhost:3001/devicesInfos")
      .then(res => { setDevices(res.data) })
      .catch(err => { console.error(err); });
    },[devices])

    // useEffect that sends the devices data to the C++ application on a Raspberry Pi
    useEffect(() => {
      Axios.get("http://localhost:3001/devicesInfos")
        .then((res) => {
          SetComponent(res.data);
          console.log("useEffect", res.data);
          const db = JSON.stringify(res.data);
          Axios.post(`http://192.168.1.120:2222`, db)
            .then((res) => { console.log("Data sent successfully:", res.data); })
            .catch((err) => { console.log(err); }
            , []);
        })
        .catch((err) => { console.log(err); });
    }, []);    

    const buttonHandle = ()=>{
      Axios.post("http://localhost:3001/addDevice", {
        identifier: identifier.current.value,
        name: name.current.value,
        status: "off"
      })
      .then(res => { 
        console.log("Data sent successfully:", res.data);
        // Update the devices state with the newly added device
        setDevices([
          ...devices, 
          {
            identifier: identifier.current.value,
            name: name.current.value,
            status: res.data.status,
          }
        ]);
       })
      .catch(err => { console.error(err); });
      const db = JSON.stringify(res.data);
      Axios.post("http://192.168.1.120:2222", db)
        .then((res) => { console.log("Data sent successfully:", res.data); })
        .catch((err) => { console.log(err); }
        , []);
    }

    const tagClickHandle = (device) => {
      try {
        console.log("id is ", device.identifier);
        Axios.get(`http://localhost:3001/Led/${device.identifier}`)
          .then((res) => {
            console.log("Data sent successfully:", res.data.devices);
            setDevices([...devices], res.data.devices);
            window.location.reload();
          })
          .catch((err) => { console.log(err);}); 
        } 
      catch (err) { 
        console.log("error", err); 
      }
    };

  return (
    <div className="deviceForm">         
      <div className="form">
        <h1>Register New Device</h1>
        <form>
          <input
            ref={identifier}
            type="text"
            id="ID"
            name="ID"
            placeholder="ID..."
          ></input>
          <input
            ref={name}
            type="text"
            id="name"
            name="name"
            placeholder="Name..."
          ></input>
          <button onClick={buttonHandle} type="button">add </button>
          </form>
      </div>
      <div className="container">
        {devices.map((device) => (
          <DeviceTag key={device._id} device={device} tagClickHandle={tagClickHandle} />
        ))}
      </div>               
    </div>
  );
}