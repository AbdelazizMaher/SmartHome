import React, { useState } from 'react';
import Axios from 'axios';
import './Fota.css';

export default function FotaUpload() {
    const [file, setFile] = useState(null);
    const [fileName, setFileName] = useState(""); // State to store the file name

    // Handle file selection
    const handleFileChange = (event) => {
        const selectedFile = event.target.files[0];
        setFile(selectedFile);
        if (selectedFile) {
            setFileName(selectedFile.name); // Set file name to display it on the UI
        } else {
            setFileName(""); // Clear the file name if no file is selected
        }
    };

    // Handle file upload
    const handleUpload = () => {
        if (!file) {
            console.error("No file selected!");
            return;
        }

        const fileReader = new FileReader();

        fileReader.onload = () => {
            const arrayBuffer = fileReader.result;

            // Check if the file is read correctly
            console.log("Selected file size:", file.size);
            console.log('File content as ArrayBuffer:', arrayBuffer);
            console.log('File size in bytes:', arrayBuffer.byteLength);      
            
            // Wrap the ArrayBuffer in a Blob for correct binary handling
            const blob = new Blob([arrayBuffer], { type: 'application/octet-stream' });

            // Axios request to upload the file as binary
            Axios.post("http://10.42.0.2:8080/upload", blob, {
                headers: {
                    'Content-Type': 'application/octet-stream'
                }
            })
            .then((res) => { console.log('File uploaded successfully:', res.data);} )
            .catch((err) => { console.error('Error uploading file:', err);} );
        };

        fileReader.onerror = () => {
            console.error('Error reading file:', fileReader.error);
        };

        // Start reading the file
        fileReader.readAsArrayBuffer(file); // Read file as ArrayBuffer for binary upload
    };

    return (
        <div className="fota-upload">
            <h2>Upload New Firmware</h2>
            <input type="file" onChange={handleFileChange} />
            {fileName && <p>Selected file: {fileName}</p>} 
            <button onClick={handleUpload}>Upload</button>
        </div>
    );
}
