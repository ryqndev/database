import React, { Component } from 'react';
import Product from './Product';
import './Products.css';

export class Products extends Component {
    render() {
        return (
            <div className="product-holder">
                {this.props.data.map((e, i) => {
                    return <Product key={i} data={e} />
                })}
            </div>
        )
    }
}

export default Products
