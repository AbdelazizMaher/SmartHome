import "./Header.css";
export default function Header() {
  return (
    <header>
      <div className="header">
        <h1 className="headerlabel"> Smart Home </h1>
        <img
          className="headerimage"
          src="images/led_header.jpg"
          alt="header"
        ></img>
      </div>
    </header>
  );
}
