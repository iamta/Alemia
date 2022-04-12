import React from 'react';
import '../stylesheets/GradeCard.css';

class GradeCard extends React.Component {
    render() {
        var color;

        if (this.props.grade < 5){
            color = 'rgb(142, 0, 14)';
        }
        else if (this.props.grade >= 5 && this.props.grade <= 7){
            color = 'rgb(251, 79, 40)';
        }
        else if (this.props.grade > 7 && this.props.grade < 9){
            color = 'rgb(252, 198, 56)';
        }
        else
            color = 'rgb(50, 172, 124)';

        return (
            <div className='grade-card' style={{backgroundColor: color}}>
                <div className='model-name'>
                    <p>{this.props.model}</p>
                </div>
                <div className='grade-value'>
                    <p>{this.props.grade}</p>
                </div>
            </div>
        );
    }
}

export default GradeCard;