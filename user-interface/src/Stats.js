import React from "react"
import {
    Container,
    Row,
    Col,
    Card,
    ListGroup,
    ListGroupItem,
    Badge,
} from "react-bootstrap"

import { Doughnut, Bar } from 'react-chartjs-2'

import "./stylesheets/Stats.css"
 
function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
      color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

class Stats extends React.Component{
    
    constructor(props){

        super(props)
        this.state = {};

    }

    render(){

        /* Model for chart used to display files data */
        const filesBarChartModel = { 
            data : {
                labels: ['Files'],
                datasets: [
                    {
                        label: 'Files',
                        backgroundColor: 'rgba(75,192,192,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.filesCount ]
                    },
                    {
                        label: 'Sources',
                        backgroundColor: 'rgba(255,0,0,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.sourcesCount]
                    },
                    {
                        label: 'Headers',
                        backgroundColor: 'rgba(0,255,0,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.headersCount]
                    }
                ]},
            options: {
                plugins: {
                    title:{
                        display: true,
                        text: 'Number of files contained in project',
                        font: { size : 18 }
                    },
                    legend:{
                        display: true,
                        position: 'right'
                    }
                }
            }};

        /* Model for chart used to display lines data */
        const linesBarChartModel = {
            data: {
                labels: ['Line count'],
                datasets: [
                    {
                        label: 'Files',
                        backgroundColor: 'rgba(75,192,192,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.linesCount ]
                    },
                    {
                        label: 'Sources',
                        backgroundColor: 'rgba(255,0,0,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.sourcesLinesCount]
                    },
                    {
                        label: 'Headers',
                        backgroundColor: 'rgba(0,255,0,1)',
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.headersLinesCount]
                    }
                ]},
            options:{
                plugins: {
                    title:{
                        display: true,
                        text: 'Number of lines per file type',
                        font: { size : 18 }
                    },
                    legend:{
                        display: true,
                        position: 'right'
                    }
                }
            }
        }
       
        /* Model for chart used to display lines data */
        let keywordsBarChartModel = {
            data: {
                labels: [ '' ],
                datasets: []
            },
            options:{
                plugins: {
                    title:{
                        display: true,
                        text: 'Number of keywords used',
                        font: { size : 18 }
                    },
                    legend:{
                        display: true,
                        position: 'right'
                    }
                }
            }
        }

        if(this.props.metadata.keyWordsList)
        {
            let keywords = Object.keys(this.props.metadata.keyWordsList)
            for(let i = 0; i < keywords.length; i++){

                keywordsBarChartModel.data.datasets.push( 
                    {
                        label: keywords[i],
                        backgroundColor: getRandomColor(),
                        borderColor: 'rgba(0,0,0,1)',
                        borderWidth: 2,
                        data: [ this.props.metadata.keyWordsList[keywords[i]]]
                    }
                )
            }
        }
        
        if(keywordsBarChartModel.data.datasets.length == 0)
            keywordsBarChartModel.data.datasets.push( 
                {
                    label: '',
                    borderWidth: 2,
                    data: [ 0 ]
                }
            )

        /* Model for functions doughnut */
        const functionsDoughnutChartModel = {
            data: {
                labels: [ 'PureVirtual', 'Virtual', 'Overloaded', 'Private', 'Protected', 'Public', 'Overriding'],
                datasets: [{
                    label: 'Functions',
                    backgroundColor: ['#B21F00', '#C9DE00', '#2FDE00', '#00A6B4', '#6800B4', '#FF0000', '#0000FF'],
                    hoverBackgroundColor: [ '#501800', '#4B5000', '#175000', '#003350', '#35014F', '#FF1111', '#1111FF'],
                    data:[ 
                        this.props.metadata.pureVirtualFunctionsCount,
                        this.props.metadata.virtualFunctionsCount,
                        this.props.metadata.overloadedFunctionsCount,
                        this.props.metadata.privateMethodsCount,
                        this.props.metadata.protectedMethodsCount,
                        this.props.metadata.publicMethodsCount,
                        this.props.metadata.overridingFunctionsCount,
                    ]
                }]
            },
            options: {
                plugins:{
                    title:{
                        display: true,
                        text: 'Functions distribution',
                        font : { size: 18 }
                    },
                    legend:{
                        display: true,
                        position: 'right'
                    }
                }
            }
        }

        return (
            <div>
             <h3>Statistics</h3>
             <Container>
                <Row className="p-4">
                    <Col>
                         <Bar data={filesBarChartModel.data} options={filesBarChartModel.options} />
                    </Col>
                    <Col>
                        <Bar data={linesBarChartModel.data} options={linesBarChartModel.options} />
                    </Col>
                </Row>
                
                <Row className="p-4">
                     <Col>
                        <Card>
                            <Card.Body>
                                <Card.Title>General information</Card.Title>
                                <Card.Text>
                                    Below are listed generic informations about classes and methods.
                                </Card.Text>
                            </Card.Body>
                            <ListGroup className="list-group-flush">
                                <ListGroupItem>Interfaces count: {this.props.metadata.interfacesCount}</ListGroupItem>
                                <ListGroupItem>Abstract classes count: {this.props.metadata.abstractClassesCount}</ListGroupItem>
                                <ListGroupItem>Classes count: {this.props.metadata.classesCount}</ListGroupItem>
                                <ListGroupItem>Derived classes count: {this.props.metadata.derivedClassesCount}</ListGroupItem>
                                <ListGroupItem>Multiple derived classes count: {this.props.metadata.multipleDerivedClassesCount}</ListGroupItem>
                                <ListGroupItem>Singleton classes count: {this.props.metadata.singletonClassesCount}</ListGroupItem>
                                <ListGroupItem>STL elements count: {this.props.metadata.stlElementsCount}</ListGroupItem>
                                <ListGroupItem>Template classes count: {this.props.metadata.templateClassesCount}</ListGroupItem>
                            </ListGroup>
                        </Card>
                    </Col>
                    <Col>
                        <Doughnut data={functionsDoughnutChartModel.data} options={functionsDoughnutChartModel.options}></Doughnut>
                    </Col>
                </Row>
                <Row className="p-4">
                    <Col>
                        <h5 class="text-center p-0 m-0">Constructors defined</h5>
                    </Col>
                </Row>
                <Row className="p-4 py-2">
                    <Col className="d-flex justify-content-center">
                        <Badge className="badge-primary m-1">Constructors ({this.props.metadata.constructorsCount})</Badge> {' '}
                        <Badge className="badge-secondary m-1">Default Constructors ({this.props.metadata.defaultConstructorsCount})</Badge>{' '}
                        <Badge className="badge-danger m-1">Constructors with parameters ({this.props.metadata.parametersConstructorCount})</Badge>{' '}
                        <Badge className="badge-success m-1">Copy Constructors ({this.props.metadata.copyConstructorsCount})</Badge> {' '}
                        <Badge className="badge-warning m-1" text="dark">Move Constructors ({this.props.metadata.moveConstructorsCount})</Badge>{' '}
                        <Badge className="badge-info m-1">Destructors ({this.props.metadata.destructorsCount})</Badge>{' '}
                    </Col>
                </Row>
                <Row className="p-4">
                    <Col>
                        <h5 class="text-center p-0 m-0">Operators overloaded</h5>
                    </Col>
                </Row>
                <Row className="p-4 py-2">
                    <Col className="d-flex justify-content-center">
                        {
                            Object.keys(this.props.metadata.overloadedOperatorsList ?? {}).map( function(operator) {
                                return <Badge className="badge-primary m-1">Operator ({operator})</Badge>
                            })
                        }
                    </Col>
                </Row>
                <Row className="p-4">
                    <Col>
                        <Bar data={keywordsBarChartModel.data} options={keywordsBarChartModel.options} />
                    </Col>
                </Row>
             </Container>
               
            </div>
        );
    }
};

export { Stats };