import {  useRef, useState, useEffect } from "react";
import Axios from "axios";

import "./DeviceForm.css";

export default function DeviceForm() {
    const identifier = useRef();
    const name = useRef();
  
    const [devices, setDevices] = useState([])
  
    useEffect(()=> {
      Axios.get("http://localhost:3001/devicesInfos")
      .then(res => { setDevices(res.data) })
      .catch(err => { console.error(err); });
    },[devices])
  
    const ButtonHandle = ()=>{
      Axios.post("http://localhost:3001/addDevice", {
        identifier: identifier.current.value,
        name: name.current.value,
        status: "off"
      })
      .then(res => { 
        console.log("Data sent successfully:", res.data);
       })
      .catch(err => { console.error(err); });
    }

  return (
    <div className="deviceForm">
      <>
      {devices.map(({_id, identifier, name, status}) => {
        return(
          <div className="Card" key={_id}>
            <ul>
              <li>Id: {identifier}</li>
              <li>Name: {name}</li>
              <li>Status: {status}</li>
            </ul>
          </div>
        )
      })}
      </>     
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
          <button onClick={ButtonHandle} type="button">add </button>
          </form>
      </div>        
    </div>
  );
}