import "./App.css"
import Header from "./components/Header";
import Background from "./components/Background";
import DeviceForm from "./components/DeviceForm";

export default function App() {

  return (
    <div>
      <Background />
      <Header />
      <DeviceForm />
    </div>
  );
}
