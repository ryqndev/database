import React, { Component } from 'react';
import {Card, CardActionArea, CardMedia, CardContent, Typography} from '@material-ui/core';

export class Product extends Component {
    render() {
        return (
            <div>
                <Card> 
                    <CardActionArea>
                        <CardMedia
                            component='img'
                            alt={this.props.data.itemName}
                            height="300"
                            image={this.props.data.itemImage}
                            title={this.props.data.itemName}
                        />
                    </CardActionArea>
                    <CardContent>
                    <Typography gutterBottom variant="h5" component="h2">
                        {this.props.data.itemName}
                    </Typography>
                    <Typography variant="body2" color="textSecondary" component="div">
                        {this.props.data.itemDescription}
                        <hr color={"#eeeeee"}/>
                        ${this.props.data.price / 100 }
                    </Typography>
                    </CardContent>
                </Card>
            </div>
        )
    }
}

export default Product
