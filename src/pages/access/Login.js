import React, { useEffect, useState } from "react";
import "./login.css";
import "../../fonts.css";

import LoginForm from "./LoginForm.js"

export default function Login() {
  return (
    <div className="container">
      <div className="main">
        <div className="logo">Paste</div>
        <div className="verDivider"></div>
        <LoginForm />
      </div>
    </div >
  )
}
