import React, { useState } from 'react';
import Axios from 'axios';
import './Fota.css';

export default function FotaUpload() {
    const [file, setFile] = useState(null);

    const handleFileChange = (event) => {
        setFile(event.target.files[0]);
    };

    const handleUpload = () => {
        const fileReader = new FileReader();

        fileReader.onload = () => {
            const arrayBuffer = fileReader.result;

            Axios.post('http://192.168.0.106:2222/upload', arrayBuffer, {
                headers: {
                    'Content-Type': 'application/octet-stream'
                }
            })
            .then((res) => { console.log('File uploaded successfully:', res.data);} )
            .catch((err) => { console.error('Error uploading file:', err);} );
        };

        if (file) {
            fileReader.readAsArrayBuffer(file);
        }
    };

    return (
        <div className="fota-upload">
            <h2>Upload New Firmware</h2>
            <input type="file" onChange={handleFileChange} />
            <button onClick={handleUpload}>Upload</button>
        </div>
    );
}
