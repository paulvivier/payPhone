import {Component} from 'angular2/core';

interface Hero {
  id: number;
  name: string;
}

@Component({
    selector: 'my-app',
    template: `
    <h1>{{title}}</h1>
    <h2>{{hero.name}} details!</h2>
    <div><label>id: </label>{{hero.id}}</div>
    <div><label>name: </label><input [(ngModel)]="hero.name" placeholder="name"></div>
    `

})
export class AppComponent { 

    public title = 'Tour of Heroes';
    public hero: Hero = {
        id: 1, 
        name: 'Windstorm'
};
}
