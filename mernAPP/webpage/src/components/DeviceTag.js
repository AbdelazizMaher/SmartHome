import './DeviceTag.css';

export default function DeviceTag({ device, tagClickHandle }) {
  return (
    <div
      key={device._id}
      className="tag-list"
      onClick={() => tagClickHandle(device)}
    >
      <h1 className="tag-item">
        <h3>
          <span className="device-id">
            {device._id}
          </span>
          {" "}{device.name}
        </h3>
        <div className="status">
          <span>Status</span>
          <div
            className="arrow"
            style={{ backgroundColor: device.status ? "green" : "red" }}
          >
            {" "}
          </div>
        </div>
      </h1>
    </div>
  );
}