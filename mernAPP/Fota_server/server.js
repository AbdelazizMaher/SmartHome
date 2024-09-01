const express = require('express');
const fs = require('fs');
const { exec } = require('child_process');

const app = express();

app.post('/upload', (req, res) => {
    const newPath = '/tmp/new_cppApp';

    const writeStream = fs.createWriteStream(newPath);

    req.pipe(writeStream);

    writeStream.on('finish', () => {
        // Remove the old binary
        exec('sudo rm /usr/bin/Device-Controller', (err) => {
            if (err) return res.status(500).send('Error removing old binary.');

            // Move the new binary
            exec(`sudo mv ${newPath} /usr/bin/Device-Controller`, (err) => {
                if (err) return res.status(500).send('Error replacing binary.');

                // Reboot
                exec('sudo reboot', (err) => {
                    if (err) return res.status(500).send('Error rebooting system.');

                    res.send('Update successful. Rebooting...');
                });
            });
        });
    });

    writeStream.on('error', (err) => {
        return res.status(500).send('Error saving file.');
    });
});

app.listen(8080, () => {
    console.log('Server listening on port 8080');
});
