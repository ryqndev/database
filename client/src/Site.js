import React, { Component } from 'react';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import IconButton from '@material-ui/core/IconButton';
import Typography from '@material-ui/core/Typography';
import MenuIcon from '@material-ui/icons/Menu';
import SearchIcon from '@material-ui/icons/Search';
import Products from './Products';
import './Site.css';


export class Site extends Component {
    
    constructor(props){
        super(props);
        this.state = {data: []};
        fetch('http://localhost:3000').then(resp => {
            return resp.json();
        }).then(resp => {
            this.setState({data: resp});
        });
    }
    updateInputValue(evt) {
        console.log(evt.target.value);
        let query;
        if(evt.target.value === ""){
            query = `select * from products`;
        }else{
            query = `select * from products where price<=${evt.target.value}`;
        }
        fetch(`http://localhost:3000/?command=${encodeURI(query)}`, {
            method: 'POST',
        }).then(resp => {
            return resp.json();
        }).then(resp => {
            this.setState({data: resp});
        });
        this.setState({
            inputValue: evt.target.value
        });
    }
    render() {
        return (
            <div>
                <AppBar position="static">
                    <Toolbar>
                    <IconButton
                        edge="start"
                        color="inherit"
                        aria-label="Open drawer"
                    >
                        <MenuIcon />
                    </IconButton>
                    <Typography variant="h6" noWrap>
                        SHOP
                    </Typography>
                    <div className="search-bar">    
                        <SearchIcon />
                        <input
                        placeholder="Search…"
                        type="text"
                        name="search"
                        value={this.state.inputValue}
                        onChange={evt => this.updateInputValue(evt)}
                        />
                    </div>
                    </Toolbar>
                </AppBar>
                <Products data={this.state.data} />
            </div>
        )
    }
}

export default Site
