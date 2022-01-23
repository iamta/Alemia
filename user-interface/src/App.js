import React from "react"
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import {
    Container,
    Jumbotron,
    Form,
    InputGroup,
    Button
} from "react-bootstrap"
import axios from "axios"
import "./stylesheets/App.css"

const API_BASE_ADDRESS = "http://127.0.0.1:3001"

function createData(name, grade) {
    return { name, grade };
}

class App extends React.Component {

    default_state = {
        current_step: 1,
        selected_filename: "Archive",
        predicted_grade: "NaN",
        adjusted_grade: "",
        projects_names:"",
        rows:[]
    }

    constructor(props) {

        super(props)

        /* Initialize the state */
        this.state = this.default_state

        /* Bind methods */
        this.selectArchive = this.selectArchive.bind(this)
        this.adjustGrade = this.adjustGrade.bind(this)
        this.sendChangeRequest = this.sendChangeRequest.bind(this)
        this.retrainModel = this.retrainModel.bind(this)
        this.restartGradingProcess = this.restartGradingProcess.bind(this)

    }

    selectArchive(event) {

        var form_data = new FormData();

        form_data.append("file", event.target.files[0])

        axios.post(API_BASE_ADDRESS + "/predict", form_data, {
            headers: {
                "Access-Control-Allow-Origin": "*",
                "Content-Type": "multipart/form-data"
            }
        }).then(response => {
            var arr=[]
            for(let i=0;i<response.data.predicted_grade.length;i++)
            {
                arr.push(createData(response.data.projects_names[i],response.data.predicted_grade[i]))
            }
            this.setState({
                current_step: 2,
                selected_filename: event.target.files[0].name,
                predicted_grade: response.data.predicted_grade,
                projects_names: response.data.projects_names,
                rows:arr
            })
            
        }).catch(error => console.log(error));
    }

    adjustGrade(event) {
        this.setState({
            adjusted_grade: event.target.value
        })
    }

    sendChangeRequest() {
        axios.get(API_BASE_ADDRESS + "/adjust_grade", {
            headers: {
                "Access-Control-Allow-Origin": "*"
            },
            params: {
                adjusted_grade: this.state.adjusted_grade
            }
        }).catch(error => console.log(error));
    }

    retrainModel() {
        axios.get(API_BASE_ADDRESS + "/retrain_model", {
            headers: {
                "Access-Control-Allow-Origin": "*"
            }
        }).catch(error => console.log(error));
    }

    restartGradingProcess() {
        this.setState(this.default_state)
    }

    render() {

        var first_step_classes = ["process-step"]
        var second_step_classes = ["process-step"]

        // Get classes for each jumbotron
        if (this.state.current_step === 1) {
            first_step_classes.push("current")
            second_step_classes.push("inactive")
        }
        else {
            first_step_classes.push("done")
            second_step_classes.push("current")
        }
        first_step_classes = first_step_classes.join(" ")
        second_step_classes = second_step_classes.join(" ")

        return (
            <div className="App">

                <Container>

                    {/* Logo and application name */}
                    <div className="logo-container">
                        <img src="images/logo.png" alt="Naevia Logo"></img>
                        <h1>Alemia</h1>
                    </div>

                    {/* Field for uploading a file */}
                    <Jumbotron className={first_step_classes}>
                        <h3>First Step</h3>
                        <p>Select the <code>.zip</code> archive containing the source code of the student you want to grade.</p>
                        <Form>
                            <Form.File
                                label={this.state.selected_filename}
                                custom
                                onChange={this.selectArchive}
                            />
                        </Form>
                    </Jumbotron>

                    {/* Place to bind the predicted grade, change it or retrain the model */}
                    <Jumbotron className={second_step_classes}>

                        <h3>Second Step</h3>
                        <p>Review the predicted grade. If you consider it is not right, create a change request to improve the machine learning models trained in the future.</p>


                        <p className="grade">
                            
                            <b>PREDICTED GRADES</b>
                            
                        </p>
                        <p></p>

                        <div>
                            {(() => {
                                if (this.state.rows=="") {
                                return (
                                    <div></div>
                                )
                                } 
                                else {
                                return (
                                    <div>
                                        <TableContainer component={Paper}>
                                            <Table sx={{ minWidth: 250 }} size="small" aria-label="a dense table">
                                                <TableHead>
                                                <TableRow>
                                                    {/* <TableCell>Dessert (100g serving)</TableCell> */}
                                                    <TableCell><b>Project Name</b></TableCell>
                                                    <TableCell><b>Grade</b></TableCell>
                                                </TableRow>
                                                </TableHead>
                                                <TableBody>
                                                    {this.state.rows.map((row) => (
                                                        <TableRow
                                                        sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                                                        >
                                                        <TableCell>{row.name}</TableCell>
                                                        <TableCell>{row.grade}</TableCell>
                                                        </TableRow>
                                                    ))}
                                                </TableBody>
                                            </Table>
                                        </TableContainer>
                                    </div>
                                )
                                }
                            })()}
                        </div>
                        
                        
                        <br>
                        </br>
                        <br>
                        </br>
                        
                        
                        
                        
                        <Form>
                            <InputGroup className="mb-3">
                                <Form.Control
                                    type="text"
                                    placeholder="Manually adjusted grade"
                                    value={this.state.adjusted_grade}
                                    onChange={this.adjustGrade}
                                />
                                <InputGroup.Append>
                                    <Button
                                        variant="outline-secondary"
                                        onClick={this.sendChangeRequest}
                                    >
                                        Send a change request
                                    </Button>
                                </InputGroup.Append>
                            </InputGroup>
                        </Form>

                        <p>Go to the next student or retrain the machine learning model. When the training process ends, the new model will automatically replace the current one.</p>

                        <Button
                            variant="secondary"
                            size="sm"
                            block
                            onClick={this.retrainModel}
                        >
                            Retrain the model
                        </Button>
                        <Button
                            variant="secondary"
                            size="sm"
                            block
                            onClick={this.restartGradingProcess}
                        >
                            Restart the grading process
                        </Button>

                    </Jumbotron>

                </Container>

            </div>
        )
    }
}

export default App