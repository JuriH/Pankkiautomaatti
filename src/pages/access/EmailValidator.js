export default function LoginForm(email) {
    const regex = /^\S +@\S + $/
    return regex.test(email)
}