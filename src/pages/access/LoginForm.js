import React, {useEffect, useState} from "react"
import styles from "./loginform.module.css"
import EmailValidator from "./EmailValidator.js"

export default function LoginForm() {
	const [loginMode, setLoginMode] = useState(true)
	const [email, setEmail] = useState("")
	const [password, setPassword] = useState("")

	const HandleEmail = (e) => {
		const email = e.target.value

		EmailValidator(email) && setEmail(email)
	}

	const HandlePassword = (e) => {
		const password = e.target.value

		password.length > 8 && setPassword(password)
	}

	return (
		<div className={styles.container}>
			<div className={styles.formContainer}>
				<form action="" method="post">
					<input
						type="email"
						name="email"
						id="email"
						placeholder="Email"
						onChange={(e) => {
							HandleEmail(e)
						}}
					></input>
					<input
						type="password"
						name="password"
						id="password"
						placeholder="Password"
						onChange={(e) => {
							HandlePassword(e)
						}}
					></input>
					<input
						type="submit"
						value={loginMode ? "Login" : "Register"}
					></input>
				</form>
			</div>

			<button
				onClick={() => loginMode ? setLoginMode(false) : setLoginMode(true)}
			>
				{loginMode
					? "Don't have an account?\nClick here to register"
					: "Already have an account?\nClick here to login"}
			</button>
		</div>
	)
}