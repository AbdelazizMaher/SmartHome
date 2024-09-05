import "./App.css"
import Header from "./components/Header";
import Background from "./components/Background";
import DeviceForm from "./components/DeviceForm";
import FotaUpload from "./components/Fota"

export default function App() {

  return (
    <div>
      <Background />
      <Header />
      <FotaUpload />
      <DeviceForm />
    </div>
  );
}
