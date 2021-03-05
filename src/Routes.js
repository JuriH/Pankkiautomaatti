import React, { Component } from "react"
import { Router, Switch, Route } from "react-router-dom"

import Login from './pages/access/Login.js'
import Frontpage from './pages/frontpage/Frontpage.js'
import history from './history'

export default class Routes extends Component {
    render() {
        return (
            <Router history={history}>
                <Switch>
                    <Route path=
                        {"/"} exact component={Login} />
                    <Route path=
                        {"/frontpage"} component={Frontpage} />
                </Switch>
            </Router>
        )
    }
}